function fibonachi(idx){
  return idx <= 1 ? idx : fibonachi(idx - 1) + fibonachi(idx - 2);
}


let n

while (true) {
  n = +prompt('Введите номер числа');
  if (!Number.isInteger(n)) {
    alert('номер числа – не число')
    continue
  } else if(n < 0) {
    alert('номер не может быть меньше нуля')
  }
  break
}


alert(fibonachi(n))
