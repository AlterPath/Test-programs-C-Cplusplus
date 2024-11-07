from tqdm import tqdm
import time
def get_fps(image, net, times):
  total_time = 0
  for _ in tqdm(range(times)):
    start = time.time()
    classes, confidences, boxes = net.detect(frame, confThreshold=0.1, nmsThreshold=0.4)
    end = time.time()
    total_time += (end-start)

  average_frame_time = total_time * 1.0 / times
  fps = 1.0 / average_frame_time
  return fps


import cv2
import matplotlib.pyplot as plt
import time

net = cv2.dnn_DetectionModel('./yolov4.cfg', './yolov4.weights')
net.setInputSize(608, 608)
net.setInputScale(1.0 / 255)
net.setInputSwapRB(True)

frame = cv2.imread('cars.jpg')

with open('coco.names', 'rt') as f:
    names = f.read().rstrip('\n').split('\n')

start = time.time()
classes, confidences, boxes = net.detect(frame, confThreshold=0.5, nmsThreshold=0.4)
end = time.time()
print("Inference time %s sec" %(end-start))
for classId, confidence, box in zip(classes.flatten(), confidences.flatten(), boxes):
  # if names[classId] != 'person':
  #   continue
  label =  '%s:%.2f' % (names[classId], confidence)
  labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 1, 1)
  left, top, width, height = box
  top = max(top, labelSize[1])
  cv2.rectangle(frame, box, color=(255, 0, 0), thickness=2)
  cv2.rectangle(frame, (left, top - labelSize[1]), (left + labelSize[0], top + baseLine), (255, 255, 255), cv2.FILLED)
  cv2.putText(frame, label, (left, top), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0))

plt.figure(figsize = (100,100))
plt.imshow(frame[:, :, ::-1])
plt.show()
# cv2.imshow('image',frame)
# cv2.waitKey(0)

