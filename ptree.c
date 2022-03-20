#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/unistd.h>
MODULE_LICENSE("DUAL BSD/GPL");

/* ------------------------------ */

#define __NR_ptree 356
#define BUFFERSIZE 1000

struct prinfo{
  pid_t parent_pid; /* process id of parent, set 0 if it has no parent*/
  pid_t pid; /* process id */
  pid_t first_child_pid; /* pid of youngest child, set 0 if it has no child */
  pid_t next_sibling_pid; /* pid of older sibling, set 0 if it has no sibling*/
  long state; /* current state of process */
  long uid; /* user id of process owner */
  char comm[64]; /* name of program executed */
};

static int (*oldcall)(void);

static void dfs(struct task_struct *task, struct prinfo *buf, int *nr) {
  int cur = *nr;
  struct prinfo *pf = buf + cur;
  struct task_struct *child;
  struct list_head *list;
  int childcnt = 0;

  (*nr)++;
  pf->state = task->state;
  pf->pid = task->pid;
  pf->uid = task->cred->uid;
  strcpy(pf->comm, task->comm);
  pf->parent_pid = (task->parent) ? task->parent->pid : 0;
  pf->first_child_pid = 0;
  pf->next_sibling_pid = 0;

  list_for_each(list, &task->children) {
    child = list_entry(list, struct task_struct, sibling);
    childcnt++;
    pf->first_child_pid = child->pid;
    dfs(child, buf, nr);
  }

  if (childcnt > 1)
    pf->next_sibling_pid = list_entry(task->sibling.next, struct task_struct, sibling)->pid;
}

static int ptree(struct prinfo *buf, int *nr) {
  struct prinfo *kbuf = kcalloc(BUFFERSIZE, sizeof(struct prinfo), GFP_KERNEL);
  int *knr = kzalloc(sizeof(int), GFP_KERNEL);

  if (kbuf == NULL || knr == NULL)
    return -1;

  *knr = 0;
  read_lock(&tasklist_lock);
  dfs(&init_task, kbuf, knr);
  read_unlock(&tasklist_lock);

  if (copy_to_user(buf, kbuf, BUFFERSIZE * sizeof(struct prinfo)))
    return -1;
  if (copy_to_user(nr, knr, sizeof(int)))
    return -1;

  kfree(kbuf);
  kfree(knr);

  return 0;
}

/* ------------------------------ */


static int addsyscall_init(void) {
  long *syscall = (long*)0xc000d8c4;
  oldcall = (int(*)(void))(syscall[__NR_ptree]);
  syscall[__NR_ptree] = (unsigned long)ptree;
  printk(KERN_INFO "module load!\n");
  return 0;
}

static void addsyscall_exit(void) {
  long *syscall = (long*)0xc000d8c4;
  syscall[__NR_ptree] = (unsigned long)oldcall;
  printk(KERN_INFO "module exit!\n");
}

module_init(addsyscall_init);
module_exit(addsyscall_exit);
// /usr/local/Caskroom/android-ndk/23b/android-ndk-r23b/toolchains/llvm/prebuilt/darwin-x86_64/bin
