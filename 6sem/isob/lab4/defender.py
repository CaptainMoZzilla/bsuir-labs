def is_login_safe(login):
    login = login.strip(' ')
    if len(login) > 40:
        return False

    correct_sym = sum(map(lambda x : x.isalnum() or x in {'@', '.'},login))

    if correct_sym != len(login):
        return False

    return True

def is_password_safe(password):
    return len(password) < 30
