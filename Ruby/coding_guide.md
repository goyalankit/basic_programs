#### Coding guide with snippets from here and there.

1. Whenever checkin for nil, ask yourself can you prevent it? 

Some common ways to prevent it.

```Ruby
class DataSource
    def self.get(id)
        return "ankit" if id == "ankit"
    end    
end

#Traditional way
record = DataSource.get("name")
if(!record.nil?)
    print record
end

#better way. Apparently this doesn't work. TODO: read on blocks, procs and lambdas
#DataSource.get("ankit") do |myrecord|
#    puts myrecord
#end

```

#### use `fetch` by default.

```
myhash = {}

default_value = myhash.fetch(:somekey) {40} #instead of using myhash[:somekey] || 40
puts default_value
```
