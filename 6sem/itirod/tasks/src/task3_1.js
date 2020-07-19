class Vector {
    constructor(x, y, z) {
        this.x = x 
        this.y = y 
        this.z = z 
    }
    get getLength() {
      return Math.sqrt(Math.pow(this.x,2) + Math.pow(this.y,2) + Math.pow(this.z,2)) 
    }
    
    static plus(a, b) {
      const rx = a.x + b.x 
      const ry = a.y + b.y 
      const rz = a.z + b.z 
      return new Vector(rx, ry, rz)
    }

    static scalar(a, b) {
      return (a.x * b.x + a.y * b.y + a.z * b.z)
    }

    toString() {
      return `{${this.x}, ${this.y}, ${this.z}}\nДлина = ${this.getLength}`
    }

    valueOf() {
      return this.getLength 
    }
  }

    let x1 = parseInt(prompt("Введите x1")), y1 = parseInt(prompt("Введите y1")), z1 =  parseInt(prompt("Введите z1")) 
        x2 = parseInt(prompt("Введите x2")), y2 = parseInt(prompt("Введите y2")), z2 = parseInt(prompt("Введите z2")) 

    let v1 = new Vector(x1, y1, z1), v2 = new Vector(x2, y2, z2) 

    alert(`V1: ${v1}, V2: ${v2}\nScalar mult.: ${Vector.scalar(v1, v2)},\nSum: ${Vector.plus(v1, v2)}\nLength v1: ${v1.valueOf()}`)
 