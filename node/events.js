var events = require('events');

var emitter = new events.EventEmitter(); // constructor

// registering a event
emitter.on('CustomEvent', function(message, status) {
  console.log(`${status}: ${message}`)
});

// emitting a event
emitter.emit('CustomEvent', "Hello World", "200");

////////////////////////////////////////////////////////////

var EventEmitter = require('events').EventEmitter;
var util = require('util');
var Person = function(name) {
  this.name = name
};

// Person prototype inherits EventEmitter
util.inherits(Person, EventEmitter);

var ben = new Person("Ben");
ben.on('speak', function(siad) {
  console.log(`${this.name} said: ${siad}`)
});

ben.emit('speak', 'You may delay but time will not');
