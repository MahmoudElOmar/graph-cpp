import cv2
import numpy as np

colors = {
    "black": (0,0,0),
    "red" : (230, 0, 0),
    "green": (0, 204, 0),
    "blue": (0, 0, 204),
    "azure": (164, 255, 255)
}

class Canvas:
    def __init__(self,width = 1280,height = 720,title = 'window') -> None:
        self.width = width
        self.height = height
        self.title = title
        self.img = 255*np.ones([self.height,self.width,3])
    
    def show(self):
        cv2.imshow(self.title, self.img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    def save(self, filename = 'graph.png'):
        cv2.imwrite(filename,self.img)

    def RGB2BGR(color):
        return (color[2],color[1],color[0])


class VisualVertex:
    def __init__(self,center,radius = 40,color = "blue",text = "A") -> None:
        self.center = center
        self.radius = radius
        self.color = self.RGB2BGR(colors[color])
        self.text = text
    
    def draw(self,canvas):
        cv2.circle(canvas.img,self.center,self.radius,self.color,2)
        TEXT_FACE = cv2.FONT_HERSHEY_DUPLEX
        TEXT_SCALE = 1
        TEXT_THICKNESS = 2
        text_size, _ = cv2.getTextSize(self.text, TEXT_FACE, TEXT_SCALE, TEXT_THICKNESS)
        text_origin = (self.center[0] - text_size[0] // 2, self.center[1] + text_size[1] // 2)
        cv2.putText(canvas.img,self.text,text_origin,TEXT_FACE,TEXT_SCALE,self.color,TEXT_THICKNESS)

    def RGB2BGR(self,color):
        return (color[2],color[1],color[0])
    def getCenter(self):
        return np.array(self.center)



class VisualEdge:
    def __init__(self,vertex1,vertex2,color = "blue",text = "1") -> None:
        self.vertex1 = vertex1
        self.vertex2 = vertex2
        self.color = self.RGB2BGR(colors[color])
        self.text = text
    
    def RGB2BGR(self,color):
        return (color[2],color[1],color[0])

    def draw(self,canvas):
        C1 = self.vertex1.getCenter()
        C2 = self.vertex2.getCenter()
        V = C2 - C1
        d = np.linalg.norm(V)

        M1 = (C1 + (self.vertex1.radius/d) * (C2 - C1)).astype(np.uint32)
        M2 = (C2 + (self.vertex2.radius/d) * (C1 - C2)).astype(np.uint32)

        cv2.line(canvas.img,tuple(M1),tuple(M2),self.color,2)

        TEXT_FACE = cv2.FONT_HERSHEY_DUPLEX
        TEXT_SCALE = 1
        TEXT_THICKNESS = 2

        text_origin = ((M1 + M2)/2).astype(np.uint32)
        text_origin -= (2 * (np.array([-V[1],V[0]])/d)).astype(np.uint32)

        cv2.putText(canvas.img,self.text,tuple(text_origin),TEXT_FACE,TEXT_SCALE,self.color,TEXT_THICKNESS)

