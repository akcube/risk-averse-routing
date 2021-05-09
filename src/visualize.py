import matplotlib.pyplot as plt
import networkx as nx

G = nx.DiGraph()

edgeList = []
pathList = []
label = {}

with open("edgeData.txt") as curfile:
    for line in curfile:
        fr, t, string = line.split()
        fro = ord(fr) - ord('0')
        to = ord(t[0]) - ord('0')
        edgeList.append((fro,to))
        label[(fro,to)] = string

textFile = open("pathData.txt", "r")
data = textFile.read().split()

for r in range(len(data)-1):
    pathList.append((ord(data[r])-ord('0'),ord(data[r+1])-ord('0')))

G.add_edges_from(edgeList)

pos = nx.spring_layout(G)

nx.draw_networkx(G,pos,node_color='#a8d3f0',edge_color='k')

nx.draw_networkx_edges(G,pos,edgelist=pathList,edge_color='r')
nx.draw_networkx_edge_labels(G,pos,edge_labels=label)

plt.axis("off")
plt.show()
