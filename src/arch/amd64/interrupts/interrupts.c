#include <arch/amd64/interrupts/interrupts.h>

void* _c_isr_handlers[256];

void interrupts_init() {
    for (int i = 0; i < 256; i++) {
        _c_isr_handlers[i] = _c_dummy_isr;
    }

    idt_init();

    // Exceptions
    idt_set_entry(0, (uint64_t)&_isr0, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(1, (uint64_t)&_isr1, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(2, (uint64_t)&_isr2, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(3, (uint64_t)&_isr3, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(4, (uint64_t)&_isr4, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(5, (uint64_t)&_isr5, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(6, (uint64_t)&_isr6, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(7, (uint64_t)&_isr7, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(8, (uint64_t)&_isr8, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(9, (uint64_t)&_isr9, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(10, (uint64_t)&_isr10, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(11, (uint64_t)&_isr11, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(12, (uint64_t)&_isr12, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(13, (uint64_t)&_isr13, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(14, (uint64_t)&_isr14, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(15, (uint64_t)&_isr15, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(16, (uint64_t)&_isr16, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(17, (uint64_t)&_isr17, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(18, (uint64_t)&_isr18, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(19, (uint64_t)&_isr19, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(20, (uint64_t)&_isr20, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(21, (uint64_t)&_isr21, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(22, (uint64_t)&_isr22, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(23, (uint64_t)&_isr23, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(24, (uint64_t)&_isr24, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(25, (uint64_t)&_isr25, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(26, (uint64_t)&_isr26, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(27, (uint64_t)&_isr27, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(28, (uint64_t)&_isr28, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(29, (uint64_t)&_isr29, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(30, (uint64_t)&_isr30, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(31, (uint64_t)&_isr31, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);

    // IRQs
    idt_set_entry(32, (uint64_t)&_isr32, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(33, (uint64_t)&_isr33, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(34, (uint64_t)&_isr34, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(35, (uint64_t)&_isr35, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(36, (uint64_t)&_isr36, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(37, (uint64_t)&_isr37, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(38, (uint64_t)&_isr38, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(39, (uint64_t)&_isr39, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(40, (uint64_t)&_isr40, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(41, (uint64_t)&_isr41, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(42, (uint64_t)&_isr42, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(43, (uint64_t)&_isr43, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(44, (uint64_t)&_isr44, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(45, (uint64_t)&_isr45, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(46, (uint64_t)&_isr46, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);
    idt_set_entry(47, (uint64_t)&_isr47, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 0);

    // Softare triggerd interrupts
    idt_set_entry(48, (uint64_t)&_isr48, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(49, (uint64_t)&_isr49, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(50, (uint64_t)&_isr50, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(51, (uint64_t)&_isr51, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(52, (uint64_t)&_isr52, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(53, (uint64_t)&_isr53, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(54, (uint64_t)&_isr54, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(55, (uint64_t)&_isr55, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(56, (uint64_t)&_isr56, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(57, (uint64_t)&_isr57, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(58, (uint64_t)&_isr58, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(59, (uint64_t)&_isr59, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(60, (uint64_t)&_isr60, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(61, (uint64_t)&_isr61, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(62, (uint64_t)&_isr62, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(63, (uint64_t)&_isr63, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(64, (uint64_t)&_isr64, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(65, (uint64_t)&_isr65, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(66, (uint64_t)&_isr66, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(67, (uint64_t)&_isr67, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(68, (uint64_t)&_isr68, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(69, (uint64_t)&_isr69, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(70, (uint64_t)&_isr70, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(71, (uint64_t)&_isr71, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(72, (uint64_t)&_isr72, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(73, (uint64_t)&_isr73, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(74, (uint64_t)&_isr74, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(75, (uint64_t)&_isr75, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(76, (uint64_t)&_isr76, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(77, (uint64_t)&_isr77, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(78, (uint64_t)&_isr78, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(79, (uint64_t)&_isr79, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(80, (uint64_t)&_isr80, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(81, (uint64_t)&_isr81, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(82, (uint64_t)&_isr82, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(83, (uint64_t)&_isr83, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(84, (uint64_t)&_isr84, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(85, (uint64_t)&_isr85, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(86, (uint64_t)&_isr86, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(87, (uint64_t)&_isr87, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(88, (uint64_t)&_isr88, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(89, (uint64_t)&_isr89, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(90, (uint64_t)&_isr90, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(91, (uint64_t)&_isr91, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(92, (uint64_t)&_isr92, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(93, (uint64_t)&_isr93, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(94, (uint64_t)&_isr94, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(95, (uint64_t)&_isr95, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(96, (uint64_t)&_isr96, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(97, (uint64_t)&_isr97, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(98, (uint64_t)&_isr98, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(99, (uint64_t)&_isr99, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(100, (uint64_t)&_isr100, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(101, (uint64_t)&_isr101, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(102, (uint64_t)&_isr102, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(103, (uint64_t)&_isr103, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(104, (uint64_t)&_isr104, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(105, (uint64_t)&_isr105, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(106, (uint64_t)&_isr106, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(107, (uint64_t)&_isr107, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(108, (uint64_t)&_isr108, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(109, (uint64_t)&_isr109, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(110, (uint64_t)&_isr110, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(111, (uint64_t)&_isr111, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(112, (uint64_t)&_isr112, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(113, (uint64_t)&_isr113, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(114, (uint64_t)&_isr114, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(115, (uint64_t)&_isr115, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(116, (uint64_t)&_isr116, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(117, (uint64_t)&_isr117, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(118, (uint64_t)&_isr118, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(119, (uint64_t)&_isr119, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(120, (uint64_t)&_isr120, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(121, (uint64_t)&_isr121, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(122, (uint64_t)&_isr122, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(123, (uint64_t)&_isr123, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(124, (uint64_t)&_isr124, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(125, (uint64_t)&_isr125, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(126, (uint64_t)&_isr126, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(127, (uint64_t)&_isr127, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(128, (uint64_t)&_isr128, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(129, (uint64_t)&_isr129, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(130, (uint64_t)&_isr130, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(131, (uint64_t)&_isr131, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(132, (uint64_t)&_isr132, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(133, (uint64_t)&_isr133, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(134, (uint64_t)&_isr134, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(135, (uint64_t)&_isr135, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(136, (uint64_t)&_isr136, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(137, (uint64_t)&_isr137, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(138, (uint64_t)&_isr138, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(139, (uint64_t)&_isr139, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(140, (uint64_t)&_isr140, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(141, (uint64_t)&_isr141, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(142, (uint64_t)&_isr142, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(143, (uint64_t)&_isr143, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(144, (uint64_t)&_isr144, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(145, (uint64_t)&_isr145, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(146, (uint64_t)&_isr146, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(147, (uint64_t)&_isr147, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(148, (uint64_t)&_isr148, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(149, (uint64_t)&_isr149, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(150, (uint64_t)&_isr150, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(151, (uint64_t)&_isr151, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(152, (uint64_t)&_isr152, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(153, (uint64_t)&_isr153, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(154, (uint64_t)&_isr154, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(155, (uint64_t)&_isr155, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(156, (uint64_t)&_isr156, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(157, (uint64_t)&_isr157, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(158, (uint64_t)&_isr158, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(159, (uint64_t)&_isr159, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(160, (uint64_t)&_isr160, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(161, (uint64_t)&_isr161, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(162, (uint64_t)&_isr162, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(163, (uint64_t)&_isr163, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(164, (uint64_t)&_isr164, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(165, (uint64_t)&_isr165, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(166, (uint64_t)&_isr166, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(167, (uint64_t)&_isr167, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(168, (uint64_t)&_isr168, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(169, (uint64_t)&_isr169, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(170, (uint64_t)&_isr170, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(171, (uint64_t)&_isr171, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(172, (uint64_t)&_isr172, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(173, (uint64_t)&_isr173, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(174, (uint64_t)&_isr174, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(175, (uint64_t)&_isr175, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(176, (uint64_t)&_isr176, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(177, (uint64_t)&_isr177, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(178, (uint64_t)&_isr178, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(179, (uint64_t)&_isr179, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(180, (uint64_t)&_isr180, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(181, (uint64_t)&_isr181, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(182, (uint64_t)&_isr182, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(183, (uint64_t)&_isr183, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(184, (uint64_t)&_isr184, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(185, (uint64_t)&_isr185, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(186, (uint64_t)&_isr186, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(187, (uint64_t)&_isr187, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(188, (uint64_t)&_isr188, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(189, (uint64_t)&_isr189, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(190, (uint64_t)&_isr190, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(191, (uint64_t)&_isr191, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(192, (uint64_t)&_isr192, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(193, (uint64_t)&_isr193, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(194, (uint64_t)&_isr194, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(195, (uint64_t)&_isr195, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(196, (uint64_t)&_isr196, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(197, (uint64_t)&_isr197, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(198, (uint64_t)&_isr198, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(199, (uint64_t)&_isr199, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(200, (uint64_t)&_isr200, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(201, (uint64_t)&_isr201, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(202, (uint64_t)&_isr202, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(203, (uint64_t)&_isr203, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(204, (uint64_t)&_isr204, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(205, (uint64_t)&_isr205, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(206, (uint64_t)&_isr206, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(207, (uint64_t)&_isr207, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(208, (uint64_t)&_isr208, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(209, (uint64_t)&_isr209, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(210, (uint64_t)&_isr210, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(211, (uint64_t)&_isr211, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(212, (uint64_t)&_isr212, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(213, (uint64_t)&_isr213, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(214, (uint64_t)&_isr214, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(215, (uint64_t)&_isr215, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(216, (uint64_t)&_isr216, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(217, (uint64_t)&_isr217, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(218, (uint64_t)&_isr218, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(219, (uint64_t)&_isr219, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(220, (uint64_t)&_isr220, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(221, (uint64_t)&_isr221, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(222, (uint64_t)&_isr222, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(223, (uint64_t)&_isr223, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(224, (uint64_t)&_isr224, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(225, (uint64_t)&_isr225, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(226, (uint64_t)&_isr226, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(227, (uint64_t)&_isr227, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(228, (uint64_t)&_isr228, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(229, (uint64_t)&_isr229, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(230, (uint64_t)&_isr230, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(231, (uint64_t)&_isr231, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(232, (uint64_t)&_isr232, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(233, (uint64_t)&_isr233, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(234, (uint64_t)&_isr234, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(235, (uint64_t)&_isr235, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(236, (uint64_t)&_isr236, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(237, (uint64_t)&_isr237, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(238, (uint64_t)&_isr238, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(239, (uint64_t)&_isr239, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(240, (uint64_t)&_isr240, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(241, (uint64_t)&_isr241, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(242, (uint64_t)&_isr242, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(243, (uint64_t)&_isr243, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(244, (uint64_t)&_isr244, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(245, (uint64_t)&_isr245, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(246, (uint64_t)&_isr246, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(247, (uint64_t)&_isr247, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(248, (uint64_t)&_isr248, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(249, (uint64_t)&_isr249, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(250, (uint64_t)&_isr250, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(251, (uint64_t)&_isr251, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(252, (uint64_t)&_isr252, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(253, (uint64_t)&_isr253, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(254, (uint64_t)&_isr254, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    idt_set_entry(255, (uint64_t)(uint64_t)&_isr255, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);

    idt_load();

    pic_init();
}

bool interrupts_is_bound(int id) {
    (void)id;
    return false; // TODO: Implement
}

void interrupts_bind_handler(int id, void (*handler)(isr_state_t*)) {
    _c_isr_handlers[id] = handler;
}

void interrupts_unbind_handler(int id) {
    _c_isr_handlers[id] = _c_dummy_isr;
}

void _c_dummy_isr(isr_state_t* state) {
    (void)state;
}

void interrupts_enable() {
    asm("sti");
}

void interrupts_disable() {
    asm("cli");
}