# Python Function Arguments

Experiments with Python function argument behaviors.

## Topics Covered

### 1. API Query String Default Value
- FastAPI `Query` with default value evaluation timing

### 2. Mutable Default Arguments
- The classic Python gotcha with mutable defaults
- Default dict/list are shared across calls

### 3. Positional-Only Arguments (`/`)
```python
def func(one, two, /):  # one and two must be positional
    pass
```

### 4. Keyword-Only Arguments (`*`)
```python
def func(*, one, two):  # one and two must be keyword
    pass
```

### 5. Mixed Arguments
```python
def func(pos_only, /, normal, *, kw_only, **kwargs):
    pass
```

## Usage

```bash
uv run python main.py
```
