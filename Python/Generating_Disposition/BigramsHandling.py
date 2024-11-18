# comes from Norgiv's script readapted to Python 3 to use the "with open..."
def datafile(name, sep='\t'):
    with open(name) as file:
        for line in file:
            yield line.split(sep)

# comes from Norgiv's script, readapted to prevent normalization
class Pdist(dict):
    def __init__(self, data=[], N=None, missingfn=None):
        for key,count in data:
            self[key] = self.get(key, 0) + int(count)
        self.N = float(N or sum(self.values()))
        self.missingfn = missingfn or (lambda k, N: 1./N)
    def __call__(self, key):
        if key in self: return self[key]
        else: return self.missingfn(key, self.N)
