from datetime import datetime
import os
import subprocess

DATE_FLAG_DIR = 'date_flag'

def _git_push(current_date):
    add_command = 'git add .'
    commit_command = 'git commit -m \'update {} diary\''.format(current_date)
    push_command = 'git push'
    for command in (add_command, commit_command, push_command):
        subprocess.run(command,
                       shell=True,
                       check=True,
                       stderr=subprocess.STDOUT)

def _send_email():
    admin_email = os.environ['ADMIN_EMAIL']
    print(admin_email)
    
def main():
    current_date = datetime.today().strftime('%Y-%m-%d')
    current_date_file_path = os.path.join(DATE_FLAG_DIR, current_date)
    if not os.path.exists(current_date_file_path):
        with open(current_date_file_path, 'a'):
            os.utime(current_date_file_path, None)
        _git_push()
        
    else:
        print('exist')

if __name__ == '__main__':
    main()
    _git_push('test2')
