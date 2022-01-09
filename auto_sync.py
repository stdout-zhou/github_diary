from datetime import datetime
from email.mime.text import MIMEText
import os
import subprocess

DATE_FLAG_DIR = 'date_flag'
EMAIL_SENDER = 'stdout@bot.com'

def _git_push(current_date):
    add_command = 'git add .'
    commit_command = 'git commit -m \'update {} diary\''.format(current_date)
    push_command = 'git push'
    for command in (add_command, commit_command, push_command):
        subprocess.run(command,
                       shell=True,
                       check=True,
                       stderr=subprocess.STDOUT)

def _send_email(current_date):
    admin_email = os.environ['ADMIN_EMAIL']

    email_subject = '{} has been sync to github successfully!'.format(current_date)
    email_content = ''
    msg = MIMEText(email_content, 'html', 'utf-8')
    msg['From'] = EMAIL_SENDER
    msg['To'] = admin_email
    msg['Subject'] = email_subject
    p = subprocess.Popen(['/usr/sbin/sendmail', '-t'], stdin=subprocess.PIPE)
    p.communicate(bytes(msg.as_string(), encoding='utf8'))


def main():
    current_date = datetime.today().strftime('%Y-%m-%d')
    current_date_file_path = os.path.join(DATE_FLAG_DIR, current_date)
    if not os.path.exists(current_date_file_path):
        with open(current_date_file_path, 'a'):
            os.utime(current_date_file_path, None)
        _git_push()
        _send_email()
        
    else:
        print('{} has exist'.format(current_date))

if __name__ == '__main__':
    main()
