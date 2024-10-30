# Что лежит в репозитории

* `template_dont_edit` – директория с шаблоном для отчёта и прототипами вспомогательных функций.

## Работа с шаблонами

1. Копируем шаблоны в корень репозитория.
2. Работаем в скопированных шаблонах.

Проверяются только файлы из корня репозитория. Даже отчёт.

# Что нужно загружать в репозиторий

1. Код проекта.
2. Отчёт. Без отчёта работа не проверяется!

# Автотесты [![Ci/CD](../../actions/workflows/ci.yaml/badge.svg?branch=main&event=workflow_dispatch)](../../actions/workflows/ci.yaml)

> [!WARNING]
> Если работа выполняется на `C`, то файл, содержащий функцию `main` должен называться `main.c`. Иначе – `main.cpp`.