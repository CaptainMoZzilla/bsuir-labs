import mysql.connector
from mysql.connector import Error
import time


from config import HOST_NAME, DATABASE,\
                   USER_NAME, PASSWORD

# connect = sqlite3.connect('users.db')
# cursor = connect.cursor()


try:
    connect = mysql.connector.connect(host=HOST_NAME, database=DATABASE,
                                      user=USER_NAME, password=PASSWORD)
except Error as e:
    print("Error while connecting to MySQL", e)
    exit()

# cursor = connect.cursor()
# cursor.execute("""CREATE TABLE IF NOT EXISTS `users`.`users` (
#                     `id` SMALLINT(2) NOT NULL AUTO_INCREMENT,
#                     `login` VARCHAR(45) NOT NULL,
#                     `password_hash` VARCHAR(100) NOT NULL,
#                     `role` VARCHAR(40) NOT NULL,
#                     PRIMARY KEY (`id`),
#                     UNIQUE INDEX `id_UNIQUE` (`id` ASC))
#                     ENGINE = InnoDB
#                     DEFAULT CHARACTER SET = utf8;
#                """)

# connect.commit()

def add_user(user):
    cursor = connect.cursor()
    cursor.executemany('INSERT INTO users VALUES (%s, %s, %s, %s)', [[int(time.time()) % 1000] + user])
    connect.commit()

def get_user_role(username, password_hash):
    cursor = connect.cursor()
    cursor.execute(f'SELECT role FROM users WHERE login="{username}" AND password_hash = "{password_hash}";')
    return cursor.fetchone()


def is_login_exist(username):
    cursor = connect.cursor()
    cursor.execute(f'SELECT role FROM users WHERE login="{username}";')
    return cursor.fetchone() is not None


def is_user_exist(username, password_hash):
    cursor = connect.cursor()
    cursor.execute(f'SELECT role FROM users WHERE login="{username}" AND password_hash = "{password_hash}";')
    return cursor.fetchone() is not None


def get_all_users():
    cursor = connect.cursor()
    cursor.execute(f'SELECT * FROM users;')
    return cursor.fetchall()

