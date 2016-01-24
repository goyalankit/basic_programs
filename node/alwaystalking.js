var sayings = [
  "I never give up.",
  "Those who abandon thier friends are worse than scums",
  "Greek didn't write obituaries, they asked one question: did he have passion",
  "They blame thier ignorance on the scripture they don't understand"
]

var interval = setInterval(function() {
  var i = Math.floor(Math.random() * sayings.length);
  process.stdout.write(`${sayings[i]} \n`);
}, 1000);

process.stdin.on('data', function(data) {
  console.log(`STDIN Data Recieved -> ${data.toString().trim()}`);
  clearInterval(interval);
  process.exit();
});
