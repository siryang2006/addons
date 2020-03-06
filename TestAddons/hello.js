// hello.js
const talModel = require('./build/Release/addon');
const TalMediaPlugin = talModel;
var obj = TalMediaPlugin.createObject(10);

console.log(obj.PlusOne());
// Prints: 'world'