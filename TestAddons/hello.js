// hello.js
const talModel = require('./build/Debug/addon');
const TalMediaPlugin = talModel;
var obj = TalMediaPlugin.createObject(10);

console.log(obj.PlusOne());

obj.handleMessage = function (message) {
	alert("i am handleMessage" + message);
}

alert("i am PlusOne:" + obj.PlusOne());
obj.InvokeCallBack();
// Prints: 'world'