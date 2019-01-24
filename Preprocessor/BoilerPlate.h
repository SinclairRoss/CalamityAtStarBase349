#pragma once

#define BOILERPLATE_DESTMOVECOPY(name) \
~name() noexcept = default; \
name(const name&) = default; \
name& operator=(const name&) = default; \
name(name&&) noexcept = default; \
name& operator=(name&&) noexcept = default;

#define BOILERPLATE_MOVECOPY(name) \
name(const name&) = default; \
name& operator=(const name&) = default; \
name(name&&) noexcept = default; \
name& operator=(name&&) noexcept = default;

#define BOILERPLATE_COPY(name) \
name(const name&) = default; \
name& operator=(const name&) = default; 