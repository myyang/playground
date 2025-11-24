import time
from transformers import pipeline

def load_model():
    print("正在載入模型... (第一次執行會從 Hugging Face Hub 下載約 260MB 的模型檔)")
    # pipeline 是 HF 最 High-level 的 API
    # 我們指定任務為 "sentiment-analysis" (情緒分析)
    # 指定模型為 "distilbert-base-uncased-finetuned-sst-2-english" (這是 HF 預設的輕量級模型)
    classifier = pipeline("sentiment-analysis", model="distilbert-base-uncased-finetuned-sst-2-english")
    print("模型載入完成！")
    return classifier

def process_reviews(classifier, reviews):
    results = []
    print(f"--- 開始處理 {len(reviews)} 筆評論 ---")
    
    for review in reviews:
        # 這裡就是核心 Inference 步驟
        # 模型會回傳類似 [{'label': 'POSITIVE', 'score': 0.99}] 的 List
        prediction = classifier(review)[0]
        
        # 整理結果 (模擬我們要存回 DB 的格式)
        result = {
            "text_preview": review[:30] + "...",
            "sentiment": prediction['label'],
            "confidence": round(prediction['score'], 4)
        }
        results.append(result)
        
    return results

if __name__ == "__main__":
    # 1. 模擬 Worker 啟動 (Cold Start)
    worker_model = load_model()

    # 2. 模擬從 Database 撈出的用戶評論 (每日 Routine 工作)
    dummy_db_data = [
        "This product is amazing! I love the new features.",  # 正面
        "The service was terrible and the app keeps crashing.", # 負面
        "It's okay, but I expected more for the price.",      # 中性/負面
        "Delivery was fast, but the item was damaged.",       # 混合
    ]

    # 3. 執行批次處理
    start_time = time.time()
    analyzed_data = process_reviews(worker_model, dummy_db_data)
    end_time = time.time()

    # 4. 顯示結果
    import json
    print(json.dumps(analyzed_data, indent=2))
    print(f"--- 處理耗時: {end_time - start_time:.2f} 秒 ---")
