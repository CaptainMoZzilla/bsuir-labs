insert_queries = {
    'model':      'INSERT INTO model (model_name) VALUES (%s)',
    'name':       'INSERT INTO name (name) VALUES (%s)',
    'surname':    'INSERT INTO surname (surname) VALUES (%s)',
    'patronymic': 'INSERT INTO patronymic (patronymic) VALUES (%s)',
    'brand':      'INSERT INTO brand (brand_name, short_brand_name) VALUES (%s, %s)',
    'color':      'INSERT INTO color (color_name, color_code) VALUES (%s, %s)',
    'driver':     'INSERT INTO driver (name_id, surname_id, patronymic_id, '\
                  'passport_number, adoption_date, phone_number, driver_license_number) '\
                  'VALUES (%s, %s, %s, %s, %s, %s, %s)',
    'car':        'INSERT INTO car (brand_id, model_id, color_id, number, oil_type) VALUES'\
                  ' (%s, %s, %s, %s, %s)',
    'pinned_car': 'INSERT INTO pinned_car (driver_id, car_id, is_active) VALUES (%s, %s, %s)',
}

tables = {
    '1': 'name',
    '2': 'surname',
    '3': 'patronymic',
    '4': 'brand',
    '5': 'model',
    '6': 'color',
    '7': 'car',
    '8': 'driver',
    '9': 'pinned_car'
}

table_columns = {
    'name':       ['id', 'name'],
    'surname':    ['id', 'surname'],
    'patronymic': ['id', 'patronymic'],
    'brand':      ['id', 'brand_name', 'short_brand_name'],
    'model':      ['id', 'model_name'],
    'color':      ['id', 'color_name', 'color_code'],
    'car':        ['id', 'brand', 'model', 'color', 'number', 'oil_type'],   
    'driver':     ['id', 'name', 'surname', 'patronymic', 'passport_number',
                   'adoption_date', 'phone_number', 'driver_license_number'],
    'pinned_car': ['id', 'name', 'surname', 'patronymic', 'brand', 'model',
                   'car_number', 'is_active']
}