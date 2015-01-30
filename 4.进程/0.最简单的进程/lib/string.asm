[section .text]
; 导出函数
global memcpy
global memset

; ------------------------------------------------------------------------
; 内存拷贝，仿 memcpy
; void *memcpy(void *es:p_dest, void *ds:p_src, int size);
memcpy:
	push ebp
	mov	ebp, esp

	push esi
	push edi
	push ecx

	mov	edi, [ebp + 8]	; Destination
	mov	esi, [ebp + 12]	; Source
	mov	ecx, [ebp + 16]	; Counter

.loop:
    ; 逐字节移动
	mov	al, [ds:esi]
	inc	esi
	mov	byte [es:edi], al
	inc	edi
	loop .loop          ; 循环

	mov	eax, [ebp + 8]  ; 返回值

	pop	ecx
	pop	edi
	pop	esi
	pop	ebp

	ret			; 函数结束，返回


; ------------------------------------------------------------------------
; 内存拷贝，仿 memset
; void memset(void *es:p_dest, char ch, int size);
memset:
	push ebp
	mov	ebp, esp

	push esi
	push edi
	push ecx

	mov	edi, [ebp + 8]	; Destination
	mov	edx, [ebp + 12]	; Char to be putted
	mov	ecx, [ebp + 16]	; Counter

.loop:
	mov	byte [edi], dl
	inc	edi
	loop .loop          ; 循环

	pop	ecx
	pop	edi
	pop	esi
	pop	ebp

	ret			; 函数结束，返回
