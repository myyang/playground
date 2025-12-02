# Concurrency Experiments

Python concurrency patterns comparison between asyncio and multiprocessing.

## Files

| File | Description |
|------|-------------|
| `asyncio_exp.py` | Asyncio-based concurrent execution |
| `mp_exp.py` | Multiprocessing-based parallel execution |
| `worker.py` | Shared worker functions |

## Usage

```bash
python asyncio_exp.py
python mp_exp.py
```

## Concepts

- `asyncio.gather` for concurrent async tasks
- Multiprocessing for CPU-bound parallelism
- Performance comparison between approaches
