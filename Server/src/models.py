from pydantic import BaseModel, Field, field_validator
from typing import Optional, List, Dict, Any
from datetime import datetime,timezone

# --- Data Models ---

class Event(BaseModel):
    event_name: Optional[str] = None
    timestamp: Optional[datetime] = None
    data: Dict[str, Any]

    @field_validator('timestamp', mode='before')
    @classmethod
    def parse_timestamp(cls, value):
        if isinstance(value, str):
            if value.endswith('Z'):
                value = value.replace('Z', '+00:00')
            return datetime.fromisoformat(value)
        return value

class EventBatch(BaseModel):
    client_version: str
    event_lib_version: str
    global_fields: Optional[Dict[str, str]] = Field(default_factory=dict)
    device_info: Optional[Dict[str, str]] = Field(default_factory=dict)
    events: List[Event]
