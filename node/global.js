var path = require("path");
var util = require("util")
var vb =  require("v8")
var readline = require("readline");

console.log(`Rock on World from ${path.basename(__filename)}`);
util.log(`Hi from ${path.basename(__dirname)}`);
util.log(vb.getHeapStatistics());

var rl = readline.createInterface(process.stdin, process.stdout)
var realPerson = {
  name: '',
  sayings: []
};

rl.question("What is the name of real person? ", function(answer) {
  realPerson.name = answer
  rl.setPrompt(`what would ${realPerson.name} say? `);
  rl.prompt();
  rl.on('line', function(saying) {
    if (saying === 'exit') {
      rl.close();
    }
    realPerson.sayings.push(saying);
    rl.setPrompt(`what else would ${realPerson.name} say? ('exit' to leave) `)
    rl.prompt();
  });
});

rl.on('close', function() {
      for (var i = 0; i < realPerson.sayings.length; ++i) {
        util.log(realPerson.sayings[i]);
      }
      process.exit();
});
