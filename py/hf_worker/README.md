# HuggingFace Inference Worker

Batch inference worker using HuggingFace Transformers for sentiment analysis.

## Features

- Load pre-trained DistilBERT model for sentiment analysis
- Batch process multiple text reviews
- Output predictions with confidence scores

## Model

- `distilbert-base-uncased-finetuned-sst-2-english`
- Lightweight (~260MB) sentiment classification model

## Usage

```bash
pip install transformers torch
python worker.py
```

## Output Example

```json
[
  {
    "text_preview": "This product is amazing!...",
    "sentiment": "POSITIVE",
    "confidence": 0.9998
  }
]
```

## Use Case

Simulates a background worker that:
1. Loads model on startup (cold start)
2. Fetches data from database
3. Runs batch inference
4. Stores results back to database
