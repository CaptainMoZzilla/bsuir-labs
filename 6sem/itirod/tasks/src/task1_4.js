function findDayAndWeek(month, day, year=2020) {
  let daysNames = ['понедельник', 'вторник', 'средa', 'четверг', 'пятницa', 'субботa', 'воскресенье'];
  let date = new Date(year, month, day);
  alert(daysNames[date.getDay()])
}


let month, day

while (true) {
  month = +prompt('Введите номер месяца');
  if (!Number.isInteger(month)) {
    alert('номер месяца – не число')
    continue
  } else if(month < 1 || month > 12) {
    alert('Month должен быть >= 1 && <= 12')
  }
  break
}

while (true) {
  day = +prompt('Введите номер дня');
  if (!Number.isInteger(day)) {
    alert('номер дня – не число')
    continue
  } else if(day < 1 || day > 31) {
    alert('Day должен быть >= 1 && <= 31')
  }
  break
}

findDayAndWeek(month - 1, day - 1)