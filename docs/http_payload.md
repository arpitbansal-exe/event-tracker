# 🌐 HTTP Payload Structure

The EventTracker SDK sends events to the server in JSON format. Below is an example payload:

```json
{
  "client_version": "1.0.0",
  "device_info": {
    "architecture": "x86_64",
    "cpu_cores": "8",
    "device_id": "90e02037-2192-4d33-9993-e8c7677b7f06",
    "hostname": "DESKTOP-D4OMPH2",
    "platform": "Windows",
    "ram_mb": "8103"
  },
  "event_lib_version": "1.0.0",
  "events": [
    {
      "event_name": "job_1",
      "timestamp": "2025-06-05T01:52:54",
      {
        "ret_value": "9483943"
      }
    },
    {
      "event_name": "job_1",
      "timestamp": "2025-06-05T01:52:54"
      {
      {
        "ret_value": "9483943",
        "error":"Some-error"
      }
      }
    }
  ],
  "global_fields": {
    "scn": "9483943"
  }
}
```

## 📋 Field Breakdown

| Field | Description |
|-------|-------------|
| `client_version` | Version of the client app integrating the SDK |
| `event_lib_version` | Internal version of the EventTracker SDK itself |
| `device_info` | System-level data collected based on `DeviceInfoFlags` |
| `events` | An array of individual events to be sent in this batch |
| `global_fields` | Global metadata that applies to every event in the batch |

## ⚠️ Notes

- Keys and values are always sent as strings.
- All timestamps are ISO 8601 formatted.
- All fields are optional, but recommended for full observability.