#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/LoadedImage.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/DiskIo2.h>
#include <Protocol/BlockIo.h>

struct MemoryMap {

    /*
     * Initial buffer size (unchanged by `GetMemoryMap` function)
     */
    UINTN buffer_size;

    /*
     * Store memory map
     */
    VOID* buffer;

    UINTN map_size;
    UINTN map_key;
    UINTN descriptor_size;
    UINTN descriptor_version;
};


EFI_STATUS GetMemoryMap(struct MemoryMap* map) {
    if (map->buffer == NULL)
        return EFI_BUFFER_TOO_SMALL;

    map->map_size = map->buffer_size;

    /*
     * gBS: global boot service variable
     */
    return gBS->GetMemoryMap(
        &map->map_size,
        (EFI_MEMORY_DESCRIPTOR*)map->buffer,
        &map->map_key,
        &map->descriptor_size,
        &map->descriptor_version);
}


EFI_STATUS SaveMemoryMap(
    struct MemoryMap* map,
    EFI_FILE_PROTOCOL* file) {

}



EFI_STATUS EFIAPI UefiMain(
    EFI_HANDLE       image_handle,
    EFI_SYSTEM_TABLE *system_table) {

    Print(L"Hello, Mikan World!\n");

    /*
     * Get memory map
     */
    CHAR8 memmap_buf[4096 * 4];  // 16KiB
    struct MemoryMap memmap = {sizeof(memmap_buf), memmap_buf, 0, 0, 0, 0};

    GetMemoryMap(&memmap);

    /*
     * Write memory map to file
     */
    EFI_FILE_PROTOCOL* root_dir;
    OpenRootDir(image_handle, &root_dir);

    EFI_FILE_PROTOCOL* memmap_file;
    root_dir->Open(
        root_dir,
        &memmap_file,
        L"\\memmap",
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
        0);

    SaveMemoryMap(&memmap, memmap_file);
    memmap_file->Close(memmap_file);

    while (1);

    return EFI_SUCCESS;
}
