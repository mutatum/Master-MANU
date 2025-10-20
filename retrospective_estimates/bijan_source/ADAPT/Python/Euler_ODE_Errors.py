import numpy as np
import matplotlib.pyplot as plt

lam = 1.0
u0 = 1.0
t_end = 60.0

def euler(dt):
    t = [0.0]
    u = [u0]
    while t[-1] < t_end - 1e-12:
        h = min(dt, t_end - t[-1])
        u.append(u[-1] - lam * u[-1] * h)
        t.append(t[-1] + h)
    return np.array(t), np.array(u)

t1, u1 = euler(1.0)
ue1 = u0 * np.exp(-lam * t1)
er1 = np.abs(ue1 - u1)

dt_values = np.geomspace(1.0, 0.001, 20)
err_u = []
err_du = []
steps = []
for dt in dt_values:
    t, u = euler(dt)
    ue = u0 * np.exp(-lam * t)
    du = np.diff(u) / np.diff(t)
    tm = t[:-1] + 0.5 * np.diff(t)
    due = -lam * u0 * np.exp(-lam * tm)
    err_u.append(np.sqrt(np.trapz((ue - u) ** 2, t)))
    err_du.append(np.sqrt(np.trapz((due - du) ** 2, tm)))
    steps.append(np.mean(np.diff(t)))
steps = np.array(steps)
order = np.argsort(steps)[::-1]

fig, axes = plt.subplots(1, 2, figsize=(12, 4))
axes[0].plot(t1, ue1, label="Exacte")
axes[0].plot(t1, u1, label="Euler")
axes[0].plot(t1, er1, label="Erreur")
axes[0].set_xlabel("Temps (s)")
axes[0].set_ylabel("Valeur")
axes[0].set_title("Solutions et erreur pour Dt=1 s")
axes[0].legend()

axes[1].loglog(steps[order], np.array(err_u)[order], marker="o", label="Erreur L2 fonction")
axes[1].loglog(steps[order], np.array(err_du)[order], marker="s", label="Erreur L2 derivee")
axes[1].set_xlabel("Dt (s)")
axes[1].set_ylabel("Erreur L2")
axes[1].set_title("Erreur L2 en fonction de Dt")
axes[1].legend()
axes[1].invert_xaxis()

plt.tight_layout()
plt.show()
