function run() {
  let num1, num2

  while (true) {
    num1 = +prompt('Введите первое число');
    if (!Number.isInteger(num1)) {
      alert('первый ввод – не число')
      continue
    }
    break
  }

  while (true) {
    num2 = +prompt('Введите второе число');
    if (!Number.isInteger(num2)) {
      alert('второй ввод – не число')
      continue
    }
      
    break
  }

  if (num1 < num2) {
    alert("первое число меньше");
    return
  } else if (num1 > num2) {
    alert("второе число меньше");
    return
  }

  alert("числа равны");
}
run()