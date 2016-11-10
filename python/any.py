def has_primary_key():
    return any(row[1] == 0 and row[9] != 'YES' for row in rows):