function replace(str){
  var map = Array.prototype.map;
  return map.call(str.toLowerCase(), function(chr){
      if (chr.match('^[a-z0-9]$'))
        return chr.charCodeAt(0) - "a".charCodeAt(0)
      else if (chr.match('^[а-я0-9]$'))
        return chr.charCodeAt(0) - "а".charCodeAt(0)
      else 
        return chr
  }).join('')
}

alert(replace(prompt('Введите строку')))