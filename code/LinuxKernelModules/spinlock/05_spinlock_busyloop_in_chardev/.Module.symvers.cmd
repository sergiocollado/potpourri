cmd_/home/sergio/repos/potpourri/code/LinuxKernelModules/spinlock/05_spinlock_busyloop_in_chardev/Module.symvers := sed 's/ko$$/o/' /home/sergio/repos/potpourri/code/LinuxKernelModules/spinlock/05_spinlock_busyloop_in_chardev/modules.order | scripts/mod/modpost -m -a  -o /home/sergio/repos/potpourri/code/LinuxKernelModules/spinlock/05_spinlock_busyloop_in_chardev/Module.symvers -e -i Module.symvers   -T -