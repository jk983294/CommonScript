import sys
import subprocess
from subprocess import Popen, PIPE

# subprocess allows you to spawn new processes, connect to their input/output/error pipes, and obtain their return codes
subprocess.call(["ls", "-l"])
subprocess.call("exit 1", shell=True)                               # 1
# return code was non-zero it raises a CalledProcessError
subprocess.check_call(["ls", "-l"])
# subprocess.check_call("exit 1", shell=True)
# return its output as a byte string. return code was non-zero it raises a CalledProcessError
subprocess.check_output(["echo", "Hello World!"])

# shell pipe
p1 = Popen(["/bin/ls", "-l", "/tmp"], stdout=PIPE)
p2 = Popen(["grep", "sys"], stdin=p1.stdout, stdout=PIPE)
p1.stdout.close()                                                   # Allow p1 to receive a SIGPIPE if p2 exits
stdout, stderr = p2.communicate()                                   # communicate return (stdout, stderr) tuple
print(file=sys.stdout)
