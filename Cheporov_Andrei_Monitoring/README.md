
# MonitoringApp — CHEPOROV ANDREI

## Описание

Приложение для мониторинга состояния Linux. Считывает загрузку CPU по ядрам и оперативную память (used/free) с заданной периодичностью.

## Сборка

```bash
mkdir build
cd build
cmake ..
make
```

## Запуск

```bash
./monitor
```

## Конфигурация

Файл `config.json` позволяет задавать:

- `period` — интервал опроса
- `metrics` — CPU и память
- `outputs` — тип вывода (console)
