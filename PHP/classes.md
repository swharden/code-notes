# Classes

```php
class ABF { 
    public $abfFileName;
    public $abfID;
    
    function ABF($abfFileName) { 
        $this->abfFileName = $abfFileName;
        $this->abfID = "TEST";
    }
} 

$abf = new ABF('X:\Data\DIC2\2013\11-2013\2013-11-22\13n22000.abf');
```
