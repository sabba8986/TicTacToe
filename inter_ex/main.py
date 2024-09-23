import sys 
import os

sys.path.append(os.path.join(os.getcwd(), 'build', 'lib.linux-x86_64-3.10'))

import spam

spam.system("ls")

