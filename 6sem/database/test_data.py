import string
import random
from datetime import datetime


def fill_tables(database):
    cursor = database.cursor()
    
    name_query = 'INSERT INTO name (name) VALUES (%s)'
    names = ['Андрей', 'Александр', 'Григорий', 'Владислав', 
             'Роман', 'Борис', 'Даниил', 'Михаил', 'Дмитрий', 'Армен']
    names = list(map(lambda x: (x, ), names))
    
    surname_query = 'INSERT INTO surname (surname) VALUES (%s);'
    surnames = ['Иванов', 'Дмитриев', 'Дударев', 'Демидов', 
                'Жмых', 'Троцкий', 'Михалков', 'Муха', 'Серый', 'Тестовый']
    surnames =  list(map(lambda x: (x, ), surnames))

    patronymic_query = 'INSERT INTO patronymic (patronymic) VALUES (%s)'
    patronymics = ['Иванович', 'Дмитриевич', 'Олегович', 'Егорович', 
                'Жмыхич', 'Андреевич', 'Михайлович', 'Владимировна', 'Данииловна', 'Дмитриевна']
    patronymics = list(map(lambda x: (x, ), patronymics))

    car_models_query = 'INSERT INTO model (model_name) VALUES (%s);'
    car_models = [''.join(random.choices(string.ascii_letters, k=4)) for _ in range(10)]
    car_models = list(map(lambda x: (x,), car_models))

    car_brands_query = 'INSERT INTO brand (brand_name, short_brand_name) VALUES (%s, %s);'
    brand_names = ['Ford', 'BMW', 'Volksagen', 'Lada', 'Geely', 'Fiat', 'Iveco', 'UAZ', 'Volvo', 'Tesla']
    short_brand_names = ['Ford', 'BMW', 'VW', 'Lada', 'Geely', 'Fiat', 'Iveco', 'UAZ', 'Volvo', 'Tesla']

    color_query = 'INSERT INTO color (color_name, color_code) VALUES (%s, %s);'
    colors = [random.randint(1000, 1e5) for _ in range(10)]
    colors_names = list(map(lambda x: f'#{x}', colors))
    colors_val = list(zip(colors_names, colors))


    cursor.executemany(name_query, names)
    database.commit()

    cursor.executemany(surname_query, surnames)
    database.commit()

    cursor.executemany(patronymic_query, patronymics)
    database.commit()

    cursor.executemany(car_models_query, car_models)
    database.commit()

    cursor.executemany(car_brands_query, list(zip(brand_names, short_brand_names)))
    database.commit()

    cursor.executemany(color_query, colors_val)
    database.commit()

    driver_query = 'INSERT INTO driver (name_id, surname_id, patronymic_id,'\
                   'passport_number, adoption_date, phone_number, driver_license_number)'\
                   ' VALUES (%s, %s, %s, %s, %s, %s, %s)' 

    drivers_names_id = []
    drivers_surnames_id = []
    drivers_patronymic_id = []

    for _ in range(10):
        cursor.execute("SELECT id from name ORDER BY RAND() LIMIT 1;")
        drivers_names_id.append(cursor.fetchone()[0])
        cursor.execute("SELECT id from surname ORDER BY RAND() LIMIT 1;")
        drivers_surnames_id.append(cursor.fetchone()[0])
        cursor.execute("SELECT id from patronymic ORDER BY RAND() LIMIT 1;")
        drivers_patronymic_id.append(cursor.fetchone()[0])

    driver_dates = [datetime.fromtimestamp(random.randint(1e9, 1e10)) for _ in range(10)]
    driver_dates = list(map(lambda x: x.strftime('%Y-%m-%d %H:%M:%S'), driver_dates))
    passport_numbers = [str(random.randint(1e4, 1e7)) for _ in range(10)]
    phone_numbers = [random.randint(1e4, 1e7) for _ in range(10)]
    driver_numbers = [str(random.randint(1e7, 1e7 + 1000)) for _ in range(10)]
    driver_values = list(zip(drivers_names_id, drivers_surnames_id, drivers_patronymic_id,
                            passport_numbers, driver_dates, phone_numbers, driver_numbers))

    car_query = 'INSERT INTO car (brand_id, model_id, color_id, number, oil_type) VALUES'\
                ' (%s, %s, %s, %s, %s)'
    cars_brand_id = []
    cars_model_id = []
    cars_color_id = []
    letters = string.ascii_letters
    cars_number = [f'{random.choice(letters)}{random.randint(1e3, 1e4)}{random.choice(letters)}' 
                for _ in range(10)]
    cars_oils_type = (['petrol']*7) + ['diesel'] * 2 + ['electro'] 

    for _ in range(10):
        cursor.execute("SELECT id from brand ORDER BY RAND() LIMIT 1;")
        cars_brand_id.append(cursor.fetchone()[0])
        cursor.execute("SELECT id from model ORDER BY RAND() LIMIT 1;")
        cars_model_id.append(cursor.fetchone()[0])
        cursor.execute("SELECT id from color ORDER BY RAND() LIMIT 1;")
        cars_color_id.append(cursor.fetchone()[0]) 

    cars_values = list(zip(cars_brand_id, cars_model_id, cars_color_id,
                            cars_number, cars_oils_type))

    pinned_car_query = 'INSERT INTO pinned_car (driver_id, car_id, is_active) VALUES (%s, %s, %s)'
    pinned_car_driver_id = []
    pinned_car_car_id = []

    cursor.execute("SELECT id from driver ORDER BY RAND() LIMIT 10;")
    pinned_car_driver_id.extend(cursor.fetchall())

    cursor.execute("SELECT id from car ORDER BY RAND() LIMIT 10;")
    pinned_car_car_id.extend(cursor.fetchall())
    pinned_car_val = list(zip(pinned_car_driver_id, pinned_car_car_id, [True]*9 + [False]))

    cursor.executemany(driver_query, driver_values)
    database.commit()

    cursor.executemany(car_query, cars_values)
    database.commit()

    cursor.executemany(pinned_car_query, pinned_car_val)

    database.commit()
