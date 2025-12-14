# CONTRIBUTING.md - Panduan Kontribusi

## 📜 Standar Commit (Conventional Commits)

Gunakan format commit berikut:

```md
<type>(<scope>): <message>
```

### 📌 Tipe Commit

| Tipe       | Deskripsi                                    |
| ---------- | -------------------------------------------- |
| `feat`     | Menambahkan fitur baru                       |
| `fix`      | Memperbaiki bug                              |
| `docs`     | Perubahan dokumentasi                        |
| `style`    | Perbaikan format, tidak mempengaruhi kode    |
| `refactor` | Refactor kode tanpa mengubah fungsionalitas  |
| `perf`     | Peningkatan performa                         |
| `test`     | Menambahkan atau memperbaiki test            |
| `chore`    | Perubahan minor (misal: update dependencies) |

### 📌 Contoh Commit

```md
feat(display): menambahkan fitur animasi transisi
fix(touch): memperbaiki bug respons sentuhan di panel
refactor(lvgl): merapikan struktur kode untuk lebih modular
```

---

## 🔥 Branching Strategy

Gunakan konvensi berikut untuk nama branch:

```md
<type>/<deskripsi-singkat>
```

| Tipe Branch | Deskripsi                     |
| ----------- | ----------------------------- |
| `feature/`  | Branch untuk fitur baru       |
| `bugfix/`   | Perbaikan bug                 |
| `hotfix/`   | Patch cepat untuk bug darurat |
| `release/`  | Branch untuk persiapan rilis  |

### 📌 Contoh Nama Branch

```bash
feature/display-animations
bugfix/touch-response-delay
hotfix/crash-on-startup
```

---

## 🔁 Pull Request (PR) Guidelines

- Pastikan kode sudah diuji sebelum membuat PR.
- Beri deskripsi yang jelas tentang perubahan yang dilakukan.
- Gunakan template PR standar berikut:

### 📌 Template PR

```md
## Ringkasan Perubahan

- Menambahkan fitur X
- Memperbaiki bug Y

## Perubahan Utama

- [x] Modul A diupdate
- [x] Perbaikan di modul B

## Cara Uji

1. Jalankan `pio run -t upload`
2. Periksa tampilan UI
3. Pastikan tidak ada error di serial monitor
```
