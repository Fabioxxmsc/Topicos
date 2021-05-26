import os

os.system("rm -rf /home/$USERNAME/sandbox_memphis/my_testcase")
os.system("memphis-gen my_testcase.yaml")
os.system("memphis-app my_testcase.yaml merge")
os.system("memphis-app my_testcase.yaml -all merge_scenario.yaml")
os.system("memphis-run my_testcase.yaml merge_scenario.yaml 50")