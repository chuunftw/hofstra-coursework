import json
from pathlib import Path

Import("env")

project = Path(env.subst("$PROJECT_DIR"))
env_file = project / ".env"
if not env_file.is_file():
    raise RuntimeError("Create .env from .env.example and enter your Wi-Fi credentials.")

credentials = {}
for number, line in enumerate(env_file.read_text(encoding="utf-8-sig").splitlines(), 1):
    line = line.strip()
    if not line or line.startswith("#"):
        continue
    key, separator, value = line.partition("=")
    key = key.strip()
    if not separator or key not in ("WIFI_SSID", "WIFI_PASSWORD") or key in credentials:
        raise RuntimeError(f"Invalid or duplicate .env setting on line {number}.")
    try:
        parsed = json.loads(value.strip())
    except ValueError:
        raise RuntimeError(f"Use a double-quoted value on .env line {number}.") from None
    if not isinstance(parsed, str) or "\0" in parsed:
        raise RuntimeError(f"Invalid credential on .env line {number}.")
    credentials[key] = parsed

if "WIFI_SSID" not in credentials or not credentials["WIFI_SSID"] or "WIFI_PASSWORD" not in credentials:
    raise RuntimeError(".env must define WIFI_SSID and WIFI_PASSWORD.")

# Generate an ignored header instead of exposing credentials in compiler flags.
generated = project / ".pio" / "generated"
generated.mkdir(parents=True, exist_ok=True)
header = generated / "wifi_secrets.h"
contents = "#pragma once\n"
for key, value in credentials.items():
    literal = "".join(f"\\{byte:03o}" for byte in value.encode("utf-8"))
    contents += f'#define {key} "{literal}"\n'
if not header.exists() or header.read_text(encoding="utf-8") != contents:
    header.write_text(contents, encoding="utf-8")
env.Append(CPPPATH=[str(generated)])
