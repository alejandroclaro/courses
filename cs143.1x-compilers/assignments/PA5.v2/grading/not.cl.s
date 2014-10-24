# start of generated code
	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	2
_bool_tag:
	.word	3
_string_tag:
	.word	4
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const8:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const5
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const7
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"./not.cl"
	.byte	0	
	.align	2
	.word	-1
int_const8:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	8
	.word	-1
int_const7:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const6:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const5:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const4:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const3:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const2:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const1:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	100
	.word	-1
int_const0:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
bool_const0:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const8
	.word	str_const3
	.word	str_const4
	.word	str_const5
	.word	str_const6
	.word	str_const7
	.word	str_const2
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	Main_protObj
	.word	Main_init
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Main.main
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	-1
Object_protObj:
	.word	6
	.word	3
	.word	Object_dispTab
	.word	-1
Main_protObj:
	.word	5
	.word	3
	.word	Main_dispTab
	.word	-1
String_protObj:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const0
	.word	0
	.word	-1
Bool_protObj:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
Int_protObj:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
Object_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bool_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Int_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
IO_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main.main:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 int_const0
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 -4($fp)
	addiu	$sp $sp -4
	la	$a0	bool_const0
	sw	$a0 -8($fp)
label0:
	lw	$a0 -4($fp)
	lw	$a0 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$a0 12($a0)
	addiu	$sp $sp 4
	lw	$s1 0($sp)
	blt	$s1 $a0 label2
	la	$a0 bool_const0
	b	label3
label2:
	la	$a0 bool_const1
label3:
	lw	$a0 12($a0)
	beqz	$a0 label1
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	beqz	$a0 label25
	la	$a0 bool_const0
	b	label26
label25:
	la	$a0 bool_const1
label26:
	lw	$a0 12($a0)
	beqz	$a0 label23
	la	$a0 bool_const0
	b	label24
label23:
	la	$a0 bool_const1
label24:
	lw	$a0 12($a0)
	beqz	$a0 label21
	la	$a0 bool_const0
	b	label22
label21:
	la	$a0 bool_const1
label22:
	lw	$a0 12($a0)
	beqz	$a0 label19
	la	$a0 bool_const0
	b	label20
label19:
	la	$a0 bool_const1
label20:
	lw	$a0 12($a0)
	beqz	$a0 label17
	la	$a0 bool_const0
	b	label18
label17:
	la	$a0 bool_const1
label18:
	lw	$a0 12($a0)
	beqz	$a0 label15
	la	$a0 bool_const0
	b	label16
label15:
	la	$a0 bool_const1
label16:
	lw	$a0 12($a0)
	beqz	$a0 label13
	la	$a0 bool_const0
	b	label14
label13:
	la	$a0 bool_const1
label14:
	lw	$a0 12($a0)
	beqz	$a0 label11
	la	$a0 bool_const0
	b	label12
label11:
	la	$a0 bool_const1
label12:
	lw	$a0 12($a0)
	beqz	$a0 label9
	la	$a0 bool_const0
	b	label10
label9:
	la	$a0 bool_const1
label10:
	lw	$a0 12($a0)
	beqz	$a0 label7
	la	$a0 bool_const0
	b	label8
label7:
	la	$a0 bool_const1
label8:
	lw	$a0 12($a0)
	beqz	$a0 label5
	la	$a0 bool_const0
	b	label6
label5:
	la	$a0 bool_const1
label6:
	move	$t1 $a0
	addiu	$sp $sp 4
	lw	$a0 0($sp)
	move	$t2 $a0
	la	$a0 bool_const0
	move	$a1 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label4
	jal	equality_test
label4:
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	beqz	$a0 label48
	la	$a0 bool_const0
	b	label49
label48:
	la	$a0 bool_const1
label49:
	lw	$a0 12($a0)
	beqz	$a0 label46
	la	$a0 bool_const0
	b	label47
label46:
	la	$a0 bool_const1
label47:
	lw	$a0 12($a0)
	beqz	$a0 label44
	la	$a0 bool_const0
	b	label45
label44:
	la	$a0 bool_const1
label45:
	lw	$a0 12($a0)
	beqz	$a0 label42
	la	$a0 bool_const0
	b	label43
label42:
	la	$a0 bool_const1
label43:
	lw	$a0 12($a0)
	beqz	$a0 label40
	la	$a0 bool_const0
	b	label41
label40:
	la	$a0 bool_const1
label41:
	lw	$a0 12($a0)
	beqz	$a0 label38
	la	$a0 bool_const0
	b	label39
label38:
	la	$a0 bool_const1
label39:
	lw	$a0 12($a0)
	beqz	$a0 label36
	la	$a0 bool_const0
	b	label37
label36:
	la	$a0 bool_const1
label37:
	lw	$a0 12($a0)
	beqz	$a0 label34
	la	$a0 bool_const0
	b	label35
label34:
	la	$a0 bool_const1
label35:
	lw	$a0 12($a0)
	beqz	$a0 label32
	la	$a0 bool_const0
	b	label33
label32:
	la	$a0 bool_const1
label33:
	lw	$a0 12($a0)
	beqz	$a0 label30
	la	$a0 bool_const0
	b	label31
label30:
	la	$a0 bool_const1
label31:
	lw	$a0 12($a0)
	beqz	$a0 label28
	la	$a0 bool_const0
	b	label29
label28:
	la	$a0 bool_const1
label29:
	move	$t1 $a0
	addiu	$sp $sp 4
	lw	$a0 0($sp)
	move	$t2 $a0
	la	$a0 bool_const0
	move	$a1 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label27
	jal	equality_test
label27:
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	beqz	$a0 label71
	la	$a0 bool_const0
	b	label72
label71:
	la	$a0 bool_const1
label72:
	lw	$a0 12($a0)
	beqz	$a0 label69
	la	$a0 bool_const0
	b	label70
label69:
	la	$a0 bool_const1
label70:
	lw	$a0 12($a0)
	beqz	$a0 label67
	la	$a0 bool_const0
	b	label68
label67:
	la	$a0 bool_const1
label68:
	lw	$a0 12($a0)
	beqz	$a0 label65
	la	$a0 bool_const0
	b	label66
label65:
	la	$a0 bool_const1
label66:
	lw	$a0 12($a0)
	beqz	$a0 label63
	la	$a0 bool_const0
	b	label64
label63:
	la	$a0 bool_const1
label64:
	lw	$a0 12($a0)
	beqz	$a0 label61
	la	$a0 bool_const0
	b	label62
label61:
	la	$a0 bool_const1
label62:
	lw	$a0 12($a0)
	beqz	$a0 label59
	la	$a0 bool_const0
	b	label60
label59:
	la	$a0 bool_const1
label60:
	lw	$a0 12($a0)
	beqz	$a0 label57
	la	$a0 bool_const0
	b	label58
label57:
	la	$a0 bool_const1
label58:
	lw	$a0 12($a0)
	beqz	$a0 label55
	la	$a0 bool_const0
	b	label56
label55:
	la	$a0 bool_const1
label56:
	lw	$a0 12($a0)
	beqz	$a0 label53
	la	$a0 bool_const0
	b	label54
label53:
	la	$a0 bool_const1
label54:
	lw	$a0 12($a0)
	beqz	$a0 label51
	la	$a0 bool_const0
	b	label52
label51:
	la	$a0 bool_const1
label52:
	move	$t1 $a0
	addiu	$sp $sp 4
	lw	$a0 0($sp)
	move	$t2 $a0
	la	$a0 bool_const0
	move	$a1 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label50
	jal	equality_test
label50:
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	beqz	$a0 label94
	la	$a0 bool_const0
	b	label95
label94:
	la	$a0 bool_const1
label95:
	lw	$a0 12($a0)
	beqz	$a0 label92
	la	$a0 bool_const0
	b	label93
label92:
	la	$a0 bool_const1
label93:
	lw	$a0 12($a0)
	beqz	$a0 label90
	la	$a0 bool_const0
	b	label91
label90:
	la	$a0 bool_const1
label91:
	lw	$a0 12($a0)
	beqz	$a0 label88
	la	$a0 bool_const0
	b	label89
label88:
	la	$a0 bool_const1
label89:
	lw	$a0 12($a0)
	beqz	$a0 label86
	la	$a0 bool_const0
	b	label87
label86:
	la	$a0 bool_const1
label87:
	lw	$a0 12($a0)
	beqz	$a0 label84
	la	$a0 bool_const0
	b	label85
label84:
	la	$a0 bool_const1
label85:
	lw	$a0 12($a0)
	beqz	$a0 label82
	la	$a0 bool_const0
	b	label83
label82:
	la	$a0 bool_const1
label83:
	lw	$a0 12($a0)
	beqz	$a0 label80
	la	$a0 bool_const0
	b	label81
label80:
	la	$a0 bool_const1
label81:
	lw	$a0 12($a0)
	beqz	$a0 label78
	la	$a0 bool_const0
	b	label79
label78:
	la	$a0 bool_const1
label79:
	lw	$a0 12($a0)
	beqz	$a0 label76
	la	$a0 bool_const0
	b	label77
label76:
	la	$a0 bool_const1
label77:
	lw	$a0 12($a0)
	beqz	$a0 label74
	la	$a0 bool_const0
	b	label75
label74:
	la	$a0 bool_const1
label75:
	move	$t1 $a0
	addiu	$sp $sp 4
	lw	$a0 0($sp)
	move	$t2 $a0
	la	$a0 bool_const0
	move	$a1 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label73
	jal	equality_test
label73:
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	beqz	$a0 label117
	la	$a0 bool_const0
	b	label118
label117:
	la	$a0 bool_const1
label118:
	lw	$a0 12($a0)
	beqz	$a0 label115
	la	$a0 bool_const0
	b	label116
label115:
	la	$a0 bool_const1
label116:
	lw	$a0 12($a0)
	beqz	$a0 label113
	la	$a0 bool_const0
	b	label114
label113:
	la	$a0 bool_const1
label114:
	lw	$a0 12($a0)
	beqz	$a0 label111
	la	$a0 bool_const0
	b	label112
label111:
	la	$a0 bool_const1
label112:
	lw	$a0 12($a0)
	beqz	$a0 label109
	la	$a0 bool_const0
	b	label110
label109:
	la	$a0 bool_const1
label110:
	lw	$a0 12($a0)
	beqz	$a0 label107
	la	$a0 bool_const0
	b	label108
label107:
	la	$a0 bool_const1
label108:
	lw	$a0 12($a0)
	beqz	$a0 label105
	la	$a0 bool_const0
	b	label106
label105:
	la	$a0 bool_const1
label106:
	lw	$a0 12($a0)
	beqz	$a0 label103
	la	$a0 bool_const0
	b	label104
label103:
	la	$a0 bool_const1
label104:
	lw	$a0 12($a0)
	beqz	$a0 label101
	la	$a0 bool_const0
	b	label102
label101:
	la	$a0 bool_const1
label102:
	lw	$a0 12($a0)
	beqz	$a0 label99
	la	$a0 bool_const0
	b	label100
label99:
	la	$a0 bool_const1
label100:
	lw	$a0 12($a0)
	beqz	$a0 label97
	la	$a0 bool_const0
	b	label98
label97:
	la	$a0 bool_const1
label98:
	move	$t1 $a0
	addiu	$sp $sp 4
	lw	$a0 0($sp)
	move	$t2 $a0
	la	$a0 bool_const0
	move	$a1 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label96
	jal	equality_test
label96:
	lw	$a0 -4($fp)
	lw	$s1 12($a0)
	sw	$s1 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const2
	jal	Object.copy
	jal	Object.copy
	lw	$t2 12($a0)
	addiu	$sp $sp 4
	lw	$s1 0($sp)
	add	$s1 $s1 $t2
	sw	$s1 12($a0)
	jal	Object.copy
	sw	$a0 -4($fp)
	b	label0
label1:
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	beqz	$a0 label119
	move	$a0 $s0
	bne	$a0 $zero label121
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label121:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	b	label120
label119:
	la	$a0 int_const0
	jal	Object.copy
label120:
	addiu	$sp $sp 4
	addiu	$sp $sp 4
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	

# end of generated code
