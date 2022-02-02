class User():
    def __init__(self, id, name, age, sex):
        self.id = id
        self.name = name
        self.age = age
        self.sex = sex

    def __getitem__(self, key):
        return self.__dict__[key]

    def __setitem__(self, key, value):
        self.__dict__[key] = value


def main():
    user = User(1, 'stdout', 22, 1)
    user['fuck'] = 'fuck'
    print(user.fuc)
    if user is not None:
        print(1)
    if user:
        print(1)


if __name__ == '__main__':
    main()
