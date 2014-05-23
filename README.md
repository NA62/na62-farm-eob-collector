na62-farm-eob-collector
=======================

This application collects special DCS data at EOB and writes it into a XML file. The DCS data is collected via Dim and the services to be read out after each EOB can be (un)registered via following two DIM command services:
- EOB_DATA_COLLECTOR/REGISTER
- EOB_DATA_COLLECTOR/UNREGISTER

The string sent to those services to (un)register several services must be of the format "$service1,$service2,...,$serviceN".

The list of services registered can found at following Dim service:
- EOB_DATA_COLLECTOR/REGISTERED

## Parameters
<dl>
  <dt>registeredServices</dt>
  <dd>A comma separated list of servies to be registered at startup.</dd>

  <dt>EOBTimeout</dt>
  <dd>The registered services will not be read out directly after an update of the EOP_TS. Instead &lt;EOBTimeout&gt; seconds will be waited to let the services generate EOB triggered data.</dd>
  
  <dt>configFile</dt>
  <dd>The files containing all EOB data will be stored in this directory.</dd>
</dl>

## Output file format
For every burst one file is created. The name is formatted the following way:
```
"burstinfo%06d-%04d.xml", runNumber, burstID
```

The format of the file is like following:

```XML
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<burst>
  <run>$runNumber</run>
  <burstID>$burstID</burstID>
  <sob>$StartOfBurstTime</sob>
  <eob>$EndOfBurstTime</eob>
  <service>
    <name>$ServiceURI</name>
    <age>$TimeSinceLastUpdateInSeconds</age>
    <value>$ValueOfTheServiceReadAfterEOB</value>
  </service>
  <service>
    ...
  </service>
</burst>
```
