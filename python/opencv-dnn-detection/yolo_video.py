import cv2
import matplotlib.pyplot as plt
import time

net = cv2.dnn_DetectionModel('./yolov4.cfg', './yolov4.weights')
net.setInputSize(608, 608)
net.setInputScale(1.0 / 255)
net.setInputSwapRB(True)


with open('coco.names', 'rt') as f:
    names = f.read().rstrip('\n').split('\n')

font = cv2.FONT_HERSHEY_SIMPLEX
# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 640)  # set video widht
cam.set(4, 480)  # set video height
# # Define min window size to be recognized as a face
minW = 0.1 * cam.get(3)
minH = 0.1 * cam.get(4)
while True:
    ret, frame = cam.read()
    # img = cv2.flip(img, -1)  # Flip vertically

    classes, confidences, boxes = net.detect(frame, confThreshold=0.1, nmsThreshold=0.4)
    # image = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    for classId, confidence, box in zip(classes.flatten(), confidences.flatten(), boxes):
      if names[classId] !=   'apple':#
        continue
      label = '%s:%.2f' % (names[classId], confidence)
      labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 1, 1)
      left, top, width, height = box
      top = max(top, labelSize[1])
      cv2.rectangle(frame, box, color=(255, 0, 0), thickness=2)
      cv2.rectangle(frame, (left, top - labelSize[1]), (left + labelSize[0], top + baseLine), (255, 255, 255),cv2.FILLED)
      cv2.putText(frame, label, (left, top), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0))
      frame = cv2.cvtColor(frame[:, :, ::-1], cv2.COLOR_BGR2RGB)

    cv2.imshow('camera', frame)
    k = cv2.waitKey(10) & 0xff
    if k == 27:
      break
cam.release()
cv2.destroyAllWindows()
