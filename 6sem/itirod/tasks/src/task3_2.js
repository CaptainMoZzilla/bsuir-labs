class Task {
      constructor(name, explanation, start, end, subTasks) {
        this.name = name
        this.explanation = explanation
        this.start = start.toDateString() 
        this.end = end.toDateString() 
        this.subTasks = subTasks || []
      }
      
      explain() {
        let baseLine = `Задача: ${this.name}\nОписание:${this.explanation}\nНачало: ${this.start} \nОкончание: ${this.end}\n`
        for (let idx in this.subTasks) {
            baseLine += '>' + this.subTasks[idx].explain()
        }

        return baseLine 
      }
  }

  class CustomTask extends Task {
    constructor(name, explanation, start, end, subTasks, percent){
      super(name, explanation, start, end, subTasks) 
      this.percent = percent 
      this.isReadyFlag = percent === 100 
    }

    explain() {
      let baseLine = `Готовность: ${this.isReadyFlag}\nПроцент готовности:${this.percent}\n`
      return (baseLine + super.explain())  
    }
  }

  
  let name = prompt("Введите название задачи") 
  let explanation = prompt("Введите описание задачи") 
  let start = new Date(prompt('Дата начала: год, месяц, день')) 
  let end = new Date(prompt('Дата конца: год, месяц, день')) 
  let percent = parseInt(prompt("Процент выполненности?")) 

  let subTask = new Task('Sub_Task', 'Something', new Date('2020, 04, 04'), new Date('2020, 05, 05'))
  let mainTask = new CustomTask(name, explanation, start, end, [subTask], percent) 
  alert(mainTask.explain())
 
