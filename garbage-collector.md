Garbage Collectors
---

Much better than you may think it is.

1. GC is extremely efficient. Much more so that malloc()
2. Dead objects cost nothing to collect.
3. GC will find all the dead objects. You don't need to help.

Much worse than you may think:

1. Yes, it really does stop for ~1 sec per live GB(in most JVMs)
2. No, GC does not mean you can't have memory leaks.

---

A **Concurrent** collector performs garbage collection work concurrently with the applications own execution.

A **parallel** collector uses multiple CPUs to perform garbage collection.
