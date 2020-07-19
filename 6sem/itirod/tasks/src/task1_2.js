function solveTask2(floorCount, porch, flatByFloor, flatNumber) {
  let flatsCount = floorCount * porch * flatByFloor
  let flatByPorch = floorCount * flatByFloor
  if (flatNumber < 1 || flatNumber > flatsCount)
    throw('Illegal data')

  let flatFloor = Math.ceil((flatNumber  - 1) % flatByPorch / flatByFloor) + 1  
  let porchNum = Math.ceil((flatNumber  - 1) / flatByPorch)

  return {porchNum, flatFloor}

}

let floorCount, porch, flatByFloor, flatNumber

while (true) {
  floorCount = +prompt('Введите количество этажей');
  if (!Number.isInteger(floorCount)) {
    alert('количество этажей – не число')
    continue
  }
  break
}

while (true) {
  porch = +prompt('Введите количество подъездов');
  if (!Number.isInteger(porch)) {
    alert('количество подъездов – не число')
    continue
  }
  break
}

while (true) {
  flatByFloor = +prompt('Введите количество квартир на этаже');
  if (!Number.isInteger(flatByFloor)) {
    alert('количество квартир на этаже – не число')
    continue
  }
  break
}

while (true) {
  flatNumber = +prompt('Введите номер квартиры');
  if (!Number.isInteger(flatNumber)) {
    alert('номер квартиры – не число')
    continue
  }
  break
}

res = solveTask2(floorCount, porch, flatByFloor, flatNumber)
alert('Подъезд: ' + res['porchNum'].toString() + '  Этаж: '+ res['flatFloor'].toString())