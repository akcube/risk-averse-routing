import matplotlib.pyplot as plt
import networkx as nx

edgeListRaw = []
pathList = []
label = {}
weights = []
col = []
edgeTraffic = {}
maxw = 0
minw = 999999999

# Reading path from file

textFile = open("pathData.txt", "r")
data = textFile.read().split()

for r in range(2,len(data)-1):
    pathList.append((int(data[r]),int(data[r+1])))

Hnode = int(data[1])

directed = int(data[0])
if directed==0:
    G = nx.Graph()
else:
    G = nx.DiGraph()

# Reading edge data from file

with open("edgeData.txt") as curfile:
    for line in curfile:
        fr, t, string, ln, wt = line.split()
        fro = int(fr)
        to = int(t)
        w = int(ln)
        traffic = int(wt)
        minw = min(minw,w)
        maxw = max(maxw,w)
        edgeListRaw.append((fro,to,w))
        label[(fro,to)] = string
        edgeTraffic[(fro,to)] = traffic
        if(directed==0):
            edgeTraffic[(to,fro)] = traffic

# Scaling weights

edgeList = []
for u,v,w in edgeListRaw:
    wt = (0.5+(2.5)*((w-minw)/(maxw-minw)))
    edgeList.append((u,v,wt))


G.add_weighted_edges_from(edgeList)  # loading edges to NetworkX graph

edges = G.edges()
widths = [G[u][v]['weight'] for u,v in edges]

# Assigning colors to nodes based on their traffic percentage
col = []

for u,v in edges:
    traf = edgeTraffic[(u,v)]
    if traf<=25:
        col.append('#00ff00')
    elif traf>25 and traf<=50:
        col.append('#ffff00')
    elif traf>50 and traf<=75:
        col.append('#ff6600')
    elif traf>75 and traf<=100:
        col.append('#ff0000')


pathCol = []
for u,v in pathList:
    traf = edgeTraffic[(u,v)]
    if traf<=25:
        pathCol.append('#00ff00')
    elif traf>25 and traf<=50:
        pathCol.append('#ffff00')
    elif traf>50 and traf<=75:
        pathCol.append('#ff6600')
    elif traf>75 and traf<=100:
        pathCol.append('#ff0000')

n = len(G.nodes())
nodeSize = max(10,300-(n/10))   # Scaling size of nodes according to number of nodes

if nodeSize>150:
    nlab = 1
else:
    nlab = 0

if nlab==1:
    Ncol = '#a8d3f0'
else:
    Ncol = '#000099'

pos = nx.kamada_kawai_layout(G)  # requires scipi

# Drawing graph using NetworkX and matplotlib

nx.draw_networkx(G,pos,node_size=nodeSize,with_labels=nlab,edge_color=col,node_color=Ncol)
nx.draw_networkx_edges(G,pos,width=3,edgelist=pathList,edge_color=pathCol)
nx.draw_networkx_edges(G,pos,width=3,alpha=0.3,edgelist=pathList,edge_color='k')
if len(G.edges())<100:
    nx.draw_networkx_edge_labels(G,pos,edge_labels=label)
plt.axis("off")
plt.show()