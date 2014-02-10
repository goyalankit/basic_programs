#### Java code snippets

---

##### Get absolute path for a file.
```
File file = new File("sample.txt"); 
System.out.println(file.getAbsolutePath());
```

---

##### Load properties from a file. Override them using another property file.
```java
 public static void initializeRun(){
        Properties prop = null;
        try {
            Properties defaultProps = new Properties();
            logger.info("$ Loading properties from default.properties");
            FileInputStream in = new FileInputStream("src/default.properties");
            defaultProps.load(in);
            in.close();

            prop  = new Properties(defaultProps);

            logger.info(" -> Overriding properties from bayou.properties");
            in = new FileInputStream("src/bayou.properties");
            prop.load(in);
            in.close();

            logger.debug(prop.getProperty("scriptName"));

        } catch (IOException e) {
            e.printStackTrace();
        }

        runScript = Boolean.parseBoolean(prop.getProperty("runScript"));
        scriptName = prop.getProperty("scriptName");
        delayInterval = Long.parseLong(prop.getProperty("delayInterval"));

    }

```

---

##### Example enum

```java
package com.ut;

public enum Commands {

    START("Start"),
    EXIT("Exot");
    
    private String description;

    Commands(String description) {
        this.description = description;
    }

    public String getDescription() {
        return this.description;
    }

    String help(){
        String help = "";
        for(Commands c :Commands.values()){
            help +=  "\n-> " + c.toString() + ": " +c.getDescription();
        }
      return help;
    }
}

```
