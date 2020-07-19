class Student {
    constructor(fio, speciality, group, marks) {
        this.fio = fio || 'noname'
        this.speciality = speciality || 'no_speciality'
        this.group = group || 'no_group'
        if (marks == undefined || marks.length != 3)
            throw 'Illegal marks array length'
        this.marks = marks
        this.average_mark = this.marks.reduce((a, b) => a + b, 0) / this.marks.length
        this.average_mark = parseFloat(this.average_mark.toFixed(1))
    }
}

class StudentManager{
    constructor() {
        this.students = []
    }

    add(student) {
        if (!(student instanceof Student))
            throw 'Add works only for students'
        
        this.students.push(student)
    }

    remove(idx) {
        this.students.splice(idx, 1);
    }

    sort(sort_by) {
        switch (sort_by) {
            case "by_average_mark":
                var comparator = function(a, b) {
                    if (a.average_mark > b.average_mark)
                        return -1
                    if (a.average_mark < b.average_mark)
                        return 1
                    return 0
                }
                this.students.sort(comparator)
                break
            case "by_group_and_marks":
                var comparator = function(a, b) {
                    if (a.group > b.group)
                        return -1
                    if (a.group < b.group)
                        return 1
                    if (a.average_mark > b.average_mark)
                        return -1
                    if (a.average_mark < b.average_mark)
                        return 1
                    return 0
                }
                this.students.sort(comparator)
                break
            default:
        }
    }

    toFieldsArray() {
        var array = []
        for (let idx in this.students) {
            let student = this.students[idx]

            array.push([student.speciality, student.group, student.fio, student.marks[0], 
                        student.marks[1], student.marks[2], student.average_mark])
        }
        return array;
    }
}

function loadTestData() {
    var manager = new StudentManager
    manager.add(new Student("Дмитрий", "POIT", "753503", [8, 9, 10]))
    manager.add(new Student("Алексей", "POIT", "753501", [1, 9, 10]))
    manager.add(new Student("Андрей", "POIT", "753505", [2, 9, 10]))
    manager.add(new Student("Олег", "POIT", "753503", [11, 9, 10]))
    manager.add(new Student("Владислав", "POIT", "753501", [9, 9, 10]))
    return manager
}

function clear_table() {
    var table = document.getElementById("myTable")
    for(var i = 2; i < table.rows.length;) {
        table.deleteRow(i);
    }
}

function search(value) {
    if (value.length > 0) {
        var custom_manager = new StudentManager
    
        for (idx in manager.students) {
            let student = manager.students[idx]
            if (student.fio.toLowerCase().includes(value.toLowerCase()))
                custom_manager.add(student)
        }
    
        clear_table()
        fill_table(custom_manager, true)
    } else {
        clear_table()
        fill_table(manager, false)
    }
    
}

function delete_row(idx) {
    manager.remove(idx)
    clear_table()
    fill_table(manager)
}

function edit_row(idx) {
    data = manager.toFieldsArray()[idx]
    document.getElementById('spec_id').value = data[0]
    document.getElementById('group_id').value = data[1]
    document.getElementById('fio_id').value = data[2]
    document.getElementById('marks_id').value = data.slice(3, 6).join(' ')
    document.getElementById('add_button').innerText = 'Изменить'
    document.getElementById('clear_edit').style = ''
    document.getElementById('current_id').value = idx
}

function clear_edit() {
    document.getElementById('fio_id').value = " "
    document.getElementById('spec_id').value = " "
    document.getElementById('group_id').value = " "
    document.getElementById('marks_id').value = " "
    document.getElementById('add_button').innerText = 'Добавить'
    document.getElementById('clear_edit').style = 'display:none'
}

function add_value(button_text) {
    if (button_text == "Добавить") {
        var spec = document.getElementById('spec_id').value
        var group = document.getElementById('group_id').value
        var fio = document.getElementById('fio_id').value
        var marks = document.getElementById('marks_id').value
        
        marks = marks.split(' ').map(x=>+x)
        console.log(marks)
        manager.add(new Student(fio, spec, group, marks))
        clear_table()
        fill_table(manager)
    } 
    else {
        var spec = document.getElementById('spec_id').value
        var group = document.getElementById('group_id').value
        var fio = document.getElementById('fio_id').value
        var marks = document.getElementById('marks_id').value

        var idx = document.getElementById('current_id').value
        marks = marks.split(' ').map(x=>+x)
        
        manager.students[idx] = new Student(fio, spec, group, marks)
        clear_edit()
        clear_table()
        fill_table(manager)
    }
}

function fill_table(manager, hide_buttons=false) {
    let table = document.getElementById("myTable");
    let data = manager.toFieldsArray()

    for(var i = 0; i < data.length; i++)
    {
        var newRow = table.insertRow(table.length);
        for(var j = 0; j < data[i].length; j++)
        {
            var cell = newRow.insertCell(j);        
            cell.innerHTML = data[i][j];   
        }
        
        if (!hide_buttons){
            var edit_button = document.createElement("BUTTON");
            edit_button.innerHTML = 'Edit'
            edit_button.setAttribute("id", i);
            edit_button.onclick = function() {
                edit_row(this.id)
            }

            var cell = newRow.insertCell(data[0].length)
            cell.appendChild(edit_button);

            var remove_button = document.createElement("BUTTON");
            remove_button.innerHTML = 'Del'
            remove_button.setAttribute("id", i);

            remove_button.onclick = function() {
                delete_row(this.id)
            }

            var cell = newRow.insertCell(data[0].length)
            cell.appendChild(remove_button);
        }   
    }
}

function sort_table(query) {
    manager.sort(query)
    clear_table()
    fill_table(manager)
}

var manager = loadTestData()
fill_table(manager)