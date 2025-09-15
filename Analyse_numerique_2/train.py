# %%
import numpy as np
import matplotlib.pyplot as plt

def u(x, c0=1, f0=1, eps = 1):

    Cf = (f0)/(c0*(np.exp(c0/eps)-1))
    Cm = -Cf
    return Cm * np.exp(x* c0/eps) + x * (f0/c0) + Cf


def solve(n,eps=1):
    f0=c0=1
    h = 1/(n+1)
    X = np.linspace(0,1,n+2)
    m1 = -eps*(np.diag(np.ones(n-1),-1) + np.diag(-2*np.ones(n))+ np.diag(np.ones(n-1),1))/h**2
    m2 = c0*(np.diag(np.ones(n))+ np.diag(-np.ones(n-1),-1))/h
    A = m1 + m2
    b = f0 * np.ones(n)
    sol=np.zeros(n+2)
    sol[1:-1] = np.linalg.solve(A, b)
    return X, sol


X, sol = solve(20)
plt.plot(X, sol)

plt.plot(X, u(X))
print(np.linalg.norm(sol-u(X), 1))
print(sum(np.abs(sol-u(X))))

print(np.linalg.norm(sol-u(X), 2))
print(np.sqrt(sum(np.abs((sol-u(X))**2))))

print(np.linalg.norm(sol-u(X), np.inf))
print(np.max(np.abs((sol-u(X)))))


# %%
ns= [8,16,32,64,128]
H = 1/np.array(ns)
for ordo in [np.inf]:
    err= []
    for n in ns:
        X, sol = solve(n)
        err += [np.linalg.norm(sol-u(X), ordo)]
    print(err)
    plt.loglog(H, err, label=str(ordo))
plt.loglog(H, H, label='h')


plt.legend()
# %%
def solve_order2(n,eps=1):
    f0=c0=1
    h = 1/(n+1)
    X = np.linspace(0,1,n+2)
    m1 = -eps*(np.diag(np.ones(n-1),-1) + np.diag(-2*np.ones(n))+ np.diag(np.ones(n-1),1))/h**2
    m2 = c0*(np.diag(np.ones(n-1),1)+ np.diag(-np.ones(n-1),-1))/(2*h)
    A = m1 + m2
    b = f0 * np.ones(n)
    sol=np.zeros(n+2)
    sol[1:-1] = np.linalg.solve(A, b)
    return X, sol

# %%

ns= [8,16,32,64,128]
H = 1/np.array(ns)
for ordo in [np.inf]:
    err= []
    for n in ns:
        X, sol = solve_order2(n)
        err += [np.linalg.norm(sol-u(X), ordo)]
    print(err)
    plt.loglog(H, err, label=str(ordo))
plt.loglog(H, H**2, label='h**2')


plt.legend()

# %%

X, sol = solve(20,eps=0.01)
plt.plot(X, sol)
X, sol = solve_order2(20,eps=0.01)
plt.plot(X, sol)

plt.plot(X, u(X))
print(np.linalg.norm(sol-u(X), 1))
print(sum(np.abs(sol-u(X))))

print(np.linalg.norm(sol-u(X), 2))
print(np.sqrt(sum(np.abs((sol-u(X))**2))))

print(np.linalg.norm(sol-u(X), np.inf))
print(np.max(np.abs((sol-u(X)))))

# %%

ns= [8,16,32,64,128]
H = 1/np.array(ns)
for ordo in [np.inf]:
    err= []
    for n in ns:
        X, sol = solve(n,eps=0.01)
        err += [np.linalg.norm(sol-u(X), ordo)]
    print(err)
    plt.loglog(H, err, label=str(ordo))
plt.loglog(H, H, label='h')

# %%
ns= [8,16,32,64,128]
H = 1/np.array(ns)
for ordo in [np.inf]:
    err= []
    for n in ns:
        X, sol = solve_order2(n,eps=0.01)
        err += [np.linalg.norm(sol-u(X), ordo)]
    print(err)
    plt.loglog(H, err, label=str(ordo))
plt.loglog(H, H**2, label='h**2')


plt.legend()
# %%
