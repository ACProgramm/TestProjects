
# D-Bus Configuration Managed

## Сборка

```bash
mkdir build && cd build
cmake ..
make
```

## Запуск

### Терминал 1:
```bash
./confManagerService
```

### Терминал 2:
```bash
./confManagerApplication1
```

### Терминал 3 (пример вызова D-Bus):
```bash
gdbus call --session --dest com.system.configurationManager --object-path /com/system/configurationManager/Application/confManagerApplication1 --method com.system.configurationManager.Application.Configuration.ChangeConfiguration "TimeoutPhrase" "'Please stop me'"
```

## Зависимости

- Qt5 (Core + DBus)
- Linux с поддержкой D-Bus
