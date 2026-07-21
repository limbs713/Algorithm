func merge(nums1 []int, m int, nums2 []int, n int) {
    // := 은 변수에 값 할당이다
    i, j, k := m-1, n-1, m+n-1 // 세미클론 안 쓴다.
    // () 안 쓴다
    // 이건 for문의 while 형태로 사용한 형태
    // nums1에 담아야 하니 nums2만 다 보면 nums1은 그대로 둬도 된다 그니까 j만 다보면 됨.
    for j >= 0 {
        // i가 남아있다면 i를 먼저 넣을 수 있으면 i를 넣자
        if i >= 0 && nums1[i] > nums2[j] {
            nums1[k] = nums1[i]
            i--
        // i가 없거나 j를 넣을 차례면 j를 넣자.
        } else {
            nums1[k] = nums2[j]
            j--
        }
        // 전체 넣어야 하는 카운트 감소
        k--
    }
}
