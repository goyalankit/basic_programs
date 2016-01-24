var spawn = require('child_process').spawn;
var cp = spawn('node', ["alwaystalking.js"]);

cp.stdout.on("data", function(data) {
  console.log(`STDOUT: ${data.toString()}`);
})

cp.on('close', function() {
  console.log("Child process closing");
  process.exit();
});

setTimeout(function() {
  cp.stdin.write('STOP');
}, 4000)
